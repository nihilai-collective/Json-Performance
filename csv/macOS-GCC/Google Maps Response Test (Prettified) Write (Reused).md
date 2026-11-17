
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 19138.8 | 0.481114 | 162.18ms | 31235 | 4890 | 274194 | 1556.42 | 2.3824 | 1(Win) | true |
| Glaze | 2677.82 | 0.608994 | 1153.66ms | 31235 | 1280 | 5.87432e+06 | 11124 | 0.411817 | 2(Loss) | true |
| simdjson (reflection) | 285.068 | 0.23618 | 5178.46ms | 31235 | 2560 | 1.55924e+08 | 104494 | 0.515397 | 3(Loss) | true |
