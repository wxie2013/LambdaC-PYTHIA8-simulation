import os, time 

def build_job_files(base_dir, job_name, nevt, seed): 

    subfile = base_dir+'/job_file/'+job_name+'.sub'
    if os.path.isdir(base_dir) == False:
        os.makedirs(base_dir)
    if os.path.isdir(base_dir+'/log/')==False:
        os.makedirs(base_dir+'/log/')
    if os.path.isdir(base_dir+'/err/')==False:
        os.makedirs(base_dir+'/err/')
    if os.path.isdir(base_dir+'/job_file/')==False:
        os.makedirs(base_dir+'/job_file/')

    # slurm jobs submission files
    fsub = open(subfile, "w")
    fsub.write('#!/bin/bash'+"\n")
    fsub.write('#SBATCH  --nodes=1'+'\n')
    fsub.write('#SBATCH  --ntasks-per-node=1'+'\n')
    fsub.write('#SBATCH --output='+base_dir+'/log/'+job_name+'.out'+'\n')
    fsub.write('#SBATCH --error='+base_dir+'/err/'+job_name+'.err'+'\n')
    fsub.write('#SBATCH --job-name="'+job_name+'"\n') 
    fsub.write('cd /home/wxie/CMSSW_11_2_0_pre9' +'\n')
    fsub.write('eval `scramv1 runtime -sh`' +'\n')
    fsub.write('/home/wxie/LambdaC-PYTHIA8-simulation/LcD0ratio '+base_dir+'/'+job_name+'.root '+str(nevt)+ " " + str(seed)+"\n")
    fsub.close()

    return subfile

# submit jobs
def submit_jobs(base_dir, njobs, nevt): 

    seed = 1
    for i in range(njobs):
        job_name = 'job'+str(i)
        subfile = build_job_files(base_dir, job_name, nevt, seed)

        os.system("sbatch  --time=4:00:00 --nodes=1 -A standby "+subfile)
        #os.system("sbatch  --time=100:00:00  -A physics "+subfile)
        seed+=1


# running the script:  python3 slum_sub.py
if __name__ == "__main__":
    njobs = 1000
    nevt = 10000000
    base_dir ='/scratch/halstead/w/wxie/B2Lc'
    #base_dir ='/scratch/brown/wxie/B2Lc'
    submit_jobs(base_dir, njobs, nevt)
