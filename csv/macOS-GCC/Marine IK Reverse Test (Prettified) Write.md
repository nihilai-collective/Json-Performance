
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6420.73 | 0.196359 | 9483.72ms | 9930848 | 320 | 2.68446e+09 | 1.47503e+06 | 0.905791 | 1(Win) | true |
| Glaze | 2904.38 | 0.873208 | 10295.8ms | 9930228 | 30 | 2.43203e+10 | 3.26066e+06 | 3.1158 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 306.215 | 0.719602 | 10010.4ms | 10018896 | 30 | 1.51249e+12 | 3.12027e+07 | 5.50805 | -(Loss) | false |
