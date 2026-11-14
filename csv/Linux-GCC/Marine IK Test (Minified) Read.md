
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21527.1 | 0.147274 | 8365.84ms | 1834197 | 320 | 4.58272e+06 | 81257 | 0.424648 | 0.114967 | 1(Win) | true |
| simdjson (stage-1) | 15386.1 | 0.0662275 | 5857.54ms | 1834197 | 1280 | 7.25644e+06 | 113689 | 0.289803 | 0.160867 | 2(Loss) | true |
