
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1335.99 | 0.092057 | 847.139ms | 11812 | 1280 | 77119.5 | 8431.8 | 0.191429 | 2.2701 | 1(Win) | true |
| Jsonifier (two-stage) | 1167.28 | 0.0647608 | 969.668ms | 11812 | 2560 | 99991.9 | 9650.51 | 0.130912 | 2.59775 | 2(Loss) | true |
| Glaze | 934.047 | 0.0542313 | 1213.71ms | 11812 | 4890 | 209179 | 12060.2 | 0.0986147 | 3.2479 | 3(Loss) | true |
| simdjson (ondemand) | 562.37 | 0.120324 | 2040.06ms | 11812 | 640 | 371780 | 20030.9 | 0.0296504 | 5.3986 | 4(Loss) | true |
