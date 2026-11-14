
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 6221.7 | 0.965252 | 9851.45ms | 9930848 | 40 | 8.63569e+09 | 1.52222e+06 | 5.22527 | -(Win) | false |
| Glaze | 2557.63 | 0.690173 | 5756.35ms | 9930228 | 30 | 1.95921e+10 | 3.70272e+06 | 2.84254 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 271.537 | 0.685279 | 10610.1ms | 10018896 | 30 | 1.74436e+12 | 3.51877e+07 | 5.44351 | -(Loss) | false |
