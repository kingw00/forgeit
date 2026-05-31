# ForgeIt: AutoBot
A tool for easily integrating `CI/CD` bots into repositories. The bot's purpose is to automate workflows, as well as build and run applications for different dependencies and versions.

# CI/CD
- The main goal is to run multiple virtual machines locally to test the build and deployment process of applications on different dependencies and versions.
- A dedicated microVM and its own hypervisor will be used as the virtual machine.
- Building, application performance testing, and bot management will be performed locally on the host. You can rent a Virtual Private Cloud for bot deployment.

## Usage
# DO NOT USE THAT WITH YOUR GITHUB TOKEN, BOT STILL UNDER CONSTRUCTION
 

### Installation
1. Clone repo. via console: `git clone https://github.com/kingw00/forgeit.git`
2. Move to clone repo.: `cd forgeit`

## Build
1. Set `build.sh` as executable: `chmod +x ./build.sh`
2. Build source code: `./build.sh`

## Config
The config is located in the project's root folder - `.env.template`. Rename the file to `.env` and fill in the details.
- `github_token` - Github token. You can get it by going to your account settings and navigating to the `Developer Settings` -> `Personal Access Token` -> `Fine-grained tokens`.
- `repo` - the repository the bot will work with (format: `username/repo_name`)
- `daemon_socket_path` - Path, where the daemon socket will be located. Default: `/tmp/forgeit_daemon.sock`

### Running
After successful completion of the build, start the daemon: 
- `./build/forgeit_daemon` and the client: `./build/forgeit_client`

## Goals
- [ ] Inetegrate Hypervisor;
- [ ] Intergrate JSON Parser;
- [ ] Create micro-Linux distributive;
- [ ] Create ForgeIt daemon;
- [ ] Create GitHub Rest API module for the C++;
- [ ] Overcoming OCD;
- [ ] Dedicated Logger.

## Docs
U can found some info about code and project.
`client` info: `docs/Client.md`
`daemon` info: `docs/Daemon.md`