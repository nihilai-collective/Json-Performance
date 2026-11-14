
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2178.75 | 0.199499 | 8017.53ms | 631514 | 160 | 4.86579e+07 | 276424 | 0.0584951 | 1(Win) | true |
| Glaze | 1939.57 | 0.349051 | 8061.05ms | 631514 | 80 | 9.39775e+07 | 310512 | 0.924635 | 2(Loss) | true |
| Jsonifier (two-stage) | 1899.11 | 0.494327 | 8161.62ms | 631514 | 80 | 1.966e+08 | 317126 | 1.66602 | 3(Loss) | true |
| simdjson (reflection) | 1622.91 | 0.329191 | 9493.56ms | 631514 | 30 | 4.47706e+07 | 371098 | 0.0666406 | 4(Loss) | true |
| simdjson (ondemand) | 1275.07 | 0.108871 | 6074.52ms | 631514 | 640 | 1.6924e+08 | 472334 | 0.445903 | 5(Loss) | true |
