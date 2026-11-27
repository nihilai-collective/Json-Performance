
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1072.99 | 0.608905 | 5699.83ms | 461466 | 40 | 2.49486e+08 | 410150 | 0.633644 | 1(Win) | true |
| Jsonifier (two-stage) | 902.269 | 0.242469 | 6607.31ms | 461466 | 640 | 8.95157e+08 | 487757 | 0.598256 | 2(Loss) | true |
| simdjson (reflection) | 817.935 | 0.152554 | 7052.99ms | 461466 | 40 | 2.69496e+07 | 538048 | 0.0468083 | 3(Loss) | true |
| Glaze | 798.929 | 0.277468 | 7409.89ms | 461466 | 40 | 9.34434e+07 | 550848 | 0.100019 | 4(Loss) | true |
| simdjson (ondemand) | 709.413 | 0.0635382 | 8007.86ms | 461466 | 640 | 9.94332e+07 | 620355 | 0.0121236 | 5(Loss) | true |
