
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3577.3 | 0.468901 | 724.615ms | 25388 | 30 | 30215.5 | 6768.2 | 0.0689024 | 0.689121 | 1(Win) | true |
| Jsonifier | 3105.52 | 0.129598 | 824.631ms | 25388 | 2560 | 261353 | 7796.41 | 0.13704 | 0.794449 | 2(Loss) | true |
| Glaze | 2523.59 | 0.0893676 | 1060.47ms | 25388 | 4890 | 359490 | 9594.2 | 0.499032 | 0.978168 | 3(Loss) | true |
| simdjson (ondemand) | 1913.96 | 0.169162 | 1327.89ms | 25388 | 1280 | 586145 | 12650.1 | 0.31291 | 1.29043 | 4(Loss) | true |
