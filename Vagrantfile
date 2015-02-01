# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  config.vm.box = "ubuntu/trusty64"
  config.ssh.forward_agent = true

  config.vm.provision "shell",
    inline: "cd /home/vagrant && make -f /vagrant/dependencies.mak install-on-ubuntu-trusty && git clone https://github.com/gadomski/cpd",
    privileged: false

  config.vm.provider "virtualbox" do |v|
    v.memory = 8192
    v.cpus = 2
  end

end
