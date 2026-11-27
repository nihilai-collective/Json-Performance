
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1946.96 | 0.135091 | 5348.15ms | 7351818 | 40 | 9.4665e+08 | 3.60112e+06 | 0.114973 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1946.07 | 0.57668 | 5469.67ms | 7351818 | 40 | 1.72665e+10 | 3.60278e+06 | 3.8226 | 1(Tie) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1728.78 | 0.655773 | 6020.54ms | 7351818 | 30 | 2.12196e+10 | 4.05559e+06 | 7.04445 | -(Loss) | false |
| simdjson (ondemand) | 1645.2 | 0.169914 | 6542.42ms | 7351818 | 30 | 1.57302e+09 | 4.26163e+06 | 0.352371 | 4(Loss) | true |
| Glaze | 1601.26 | 0.0688583 | 6662.75ms | 7351818 | 40 | 3.63611e+08 | 4.37857e+06 | 0.0376276 | 5(Loss) | true |
