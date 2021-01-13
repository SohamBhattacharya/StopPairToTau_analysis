* Intitial setup:
    * `cmsrel CMSSW_10_5_0`
    * `cd CMSSW_10_5_0/src`
    * `cmsenv`
    * `git clone https://github.com/SohamBhattacharya/StopPair_analysis.git .`
    * `cd stopPair`
    * `tar -xvf resources.tar.gz`
    * `tar -xvf sourceFiles.tar.gz`
    * `chmod +x compile.sh`
    * Change CUSTOM_HEADER_PATH in `compile.sh`.
    * Change DIR and X509_USER_PROXY in `condor_script.sh`.

* To compile any file for local test, use: `./compile.sh ch code.cc`. This will creade an executable called `code`.
* The different analysis jobs can be submitted using `run_condor_mod.py`.
* The condor jobs can be managed using `findFailedCondorJobs.py`.
* The resulting output files can be hadded using `run_hadd.py`.

* Need to produce these just once (to be used by the analysis):
    * signal gen-param info (after that, remember to run `stopPair_mc/computeXSweight.py` from inside `stopPair_mc`)
    * pileup
    * b-tagging efficiency histograms
    * tau fake rate
    * tau id-iso efficiency (prompt rate)

