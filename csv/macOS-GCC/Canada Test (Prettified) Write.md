
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7390.66 | 0.186825 | 5849.19ms | 6661989 | 40 | 1.03174e+08 | 859648 | 0.195936 | 1(Win) | true |
| Glaze | 3616.86 | 0.0503391 | 5555.24ms | 6661897 | 160 | 1.25102e+08 | 1.75657e+06 | 0.264632 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 343.636 | 0.653491 | 6359.24ms | 6661989 | 30 | 4.37936e+11 | 1.84886e+07 | 18.2445 | -(Loss) | false |
