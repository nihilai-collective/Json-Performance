
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1311.04 | 0.15346 | 1002.87ms | 11812 | 4890 | 850192 | 8592.27 | 0.114747 | 1.88245 | 1(Win) | true |
| Jsonifier (two-stage) | 1130.19 | 0.145603 | 1134.71ms | 11812 | 4890 | 1.0299e+06 | 9967.18 | 0.180051 | 2.18457 | 2(Loss) | true |
| Glaze | 906.308 | 0.133697 | 1330.1ms | 11812 | 4890 | 1.35036e+06 | 12429.3 | 0.318027 | 2.72585 | 3(Loss) | true |
| simdjson (ondemand) | 623.053 | 0.53636 | 1933.55ms | 11812 | 160 | 1.50463e+06 | 18080 | 0.0828958 | 3.96698 | 4(Loss) | true |
