
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2469.29 | 0.185187 | 5741.34ms | 9930848 | 80 | 4.03587e+09 | 3.83543e+06 | 0.41947 | 1.23083 | 1(Win) | true |
| Glaze | 1278.04 | 0.0740644 | 5205.82ms | 9930228 | 40 | 1.20479e+09 | 7.40997e+06 | 0.0991653 | 2.37817 | 2(Loss) | true |
