
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6755.26 | 0.641905 | 9594.64ms | 10018896 | 40 | 3.2973e+09 | 1.41442e+06 | 0.396888 | 1(Win) | true |
| Glaze | 2709.99 | 0.248056 | 5291.87ms | 9930228 | 40 | 3.00569e+09 | 3.49455e+06 | 0.420671 | 2(Loss) | true |
| simdjson (reflection) | 324.178 | 0.277395 | 9081ms | 10018896 | 30 | 2.00536e+11 | 2.94738e+07 | 0.643232 | 3(Loss) | true |
