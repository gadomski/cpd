RELEASE_NOTES_DIR=doc/release-notes
CHANGES_FILE=CHANGES.md
CURRENT_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)


%:
	@[ "$(CURRENT_BRANCH)" == "master" ] || \
		(echo "ERROR: Must be on master to cut a release" && exit 1)
	@grep $@ $(CHANGES_FILE) || \
		(echo "ERROR: Add changes for $@ to $(CHANGES_FILE)" && exit 1)
	@[ -f $(RELEASE_NOTES_DIR)/$@.md ] || \
		(echo "ERROR: Create release notes at $(RELEASE_NOTES_DIR)/$@.md" && exit 1)
	git add $(CHANGES_FILE) $(RELEASE_NOTES_DIR)/$@.md
	git commit -m "Release: $@"
	git tag -F $(RELEASE_NOTES_DIR)/$@.md $@
	git checkout production
	git merge --ff-only master
	if ["$(suffix $@)" == ".0"]; then \
		echo "DETECTED: Not a tiny release"; \
		git checkout -b $(basename $@); \
	else \
		echo "DETECTED: Tiny release"; \
		git checkout $(basename $@); \
		git merge --ff-only master; \
	fi
	git checkout master
	@echo "REMEMBER: Don't forget to create a new release in the Github interface using these release notes. https://github.com/gadomski/cpd/releases/new"
	@echo "REMEMBER: To push up your changes, run this command:"
	@echo "git push origin master production $(basename $@) --tags"
