
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6624.93 | 1.00618 | 5988.88ms | 6661897 | 40 | 3.72428e+09 | 958995 | 0.97963 | 1(Win) | true |
| Glaze | 3120.81 | 0.583412 | 6349.16ms | 6661897 | 40 | 5.6425e+09 | 2.03578e+06 | 0.591905 | 2(Loss) | true |
| simdjson (reflection) | 266.976 | 0.828874 | 7403.07ms | 6661989 | 30 | 1.16724e+12 | 2.37975e+07 | 2.13355 | 3(Loss) | true |
