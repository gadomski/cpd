Steps to create a new cpd release
=================================

1. Create a local branch for your release, e.g. `release/v0.2.0`
2. Update CHANGES.md with all new, changed, or fixed features (use `git log <my last release>...HEAD`)
3. Create release notes in `doc/release-notes/v0.2.0.md`
   - For tiny releases, these are often just a copy-paste of the changes
   - For larger releases, these can be an abbreviated summary with the big hits only
3. Once things are lookin' good, squash `release/v0.2.0` onto master and down to one commit
4. `git checkout master`
4. `git merge --ff-only release/v0.2.0`
4. `git checkout production`
4. `git merge --ff-only master`
4. If this is a tiny release, update the appropriate minor version branch (e.g. `v0.2`) — otherwise, create a new branch for this minor version
5. `git tag -F doc/release-notes/v0.2.0.md v0.2.0`
6. `git push origin master production v0.2 --tags`
7. `git brach -d release/v0.2.0`
8. Use the github interface to create a new release in the interface
