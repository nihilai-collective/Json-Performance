
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21834.5 | 0.0704451 | 8145.02ms | 1834197 | 2560 | 8.15357e+06 | 80113 | 0.0974589 | 0.11335 | 1(Win) | true |
| simdjson (stage-1) | 15474.6 | 0.0813329 | 5782.96ms | 1834197 | 1280 | 1.08193e+07 | 113039 | 0.107246 | 0.159945 | 2(Loss) | true |
