
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.11 | 0.944528 | 5774.08ms | 7351818 | 40 | 5.10279e+10 | 3.78145e+06 | 2.10659 | 1(Win) | true |
| Jsonifier (two-stage) | 1763.72 | 0.354918 | 6169.52ms | 7351818 | 30 | 5.97186e+09 | 3.97526e+06 | 0.632656 | 2(Loss) | true |
| simdjson (reflection) | 1618.44 | 0.399733 | 6531.63ms | 7351818 | 40 | 1.19949e+10 | 4.3321e+06 | 0.859156 | 3(Loss) | true |
| Glaze | 1450.04 | 0.25475 | 7361.17ms | 7351818 | 80 | 1.21381e+10 | 4.83521e+06 | 4.02442 | 4(Loss) | true |
| simdjson (ondemand) | 1430.55 | 0.401323 | 7368.76ms | 7351818 | 40 | 1.54751e+10 | 4.90108e+06 | 0.00113171 | 5(Loss) | true |
