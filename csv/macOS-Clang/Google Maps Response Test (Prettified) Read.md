
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2939.96 | 0.0425702 | 836.588ms | 25388 | 40 | 491.638 | 8235.45 | 0.0431249 | 1(Win) | true |
| Jsonifier (two-stage) | 2306.7 | 0.0394681 | 1066.92ms | 25388 | 80 | 1372.95 | 10496.3 | 0.0153602 | 2(Loss) | true |
| Glaze | 1764.34 | 0.13427 | 1394.53ms | 25388 | 40 | 13580.3 | 13722.9 | 0.0251949 | 3(Loss) | true |
| simdjson (ondemand) | 1631.64 | 0.062362 | 1507.76ms | 25388 | 80 | 6850.78 | 14839 | 0.108953 | 4(Loss) | true |
