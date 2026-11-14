
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5888.49 | 1.34264 | 7414.85ms | 7351818 | 40 | 1.02225e+10 | 1.19067e+06 | 0.0986413 | 1(Win) | true |
| simdjson (stage-1) | 5723.66 | 0.478794 | 8073.54ms | 7351818 | 160 | 5.50376e+09 | 1.22496e+06 | 3.75559 | 2(Loss) | true |
