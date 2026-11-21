
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2499.29 | 0.408472 | 1104.85ms | 25388 | 160 | 250535 | 9687.5 | 0.115994 | 0.987761 | 1(Win) | true |
| Jsonifier | 2428.92 | 0.263933 | 1102.69ms | 25388 | 2560 | 1.77198e+06 | 9968.16 | 0.117033 | 1.01641 | 2(Loss) | true |
| Glaze | 1575.55 | 0.223948 | 1672.13ms | 25388 | 1280 | 1.516e+06 | 15367.3 | 0.223697 | 1.56856 | 3(Loss) | true |
| simdjson (ondemand) | 1363.76 | 0.583893 | 1921.83ms | 25388 | 160 | 1.71936e+06 | 17753.8 | 0.0773885 | 1.81313 | 4(Loss) | true |
