
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20712 | 0.734165 | 148.74ms | 31235 | 2560 | 285407 | 1438.2 | 0.704225 | 1(Win) | true |
| Glaze | 3056.06 | 0.730779 | 1007.57ms | 31235 | 40 | 202952 | 9747.2 | 0.109553 | 2(Loss) | true |
| simdjson (reflection) | 312.182 | 0.104955 | 9653.69ms | 31235 | 640 | 6.41886e+06 | 95418.8 | 0.0012576 | 3(Loss) | true |
