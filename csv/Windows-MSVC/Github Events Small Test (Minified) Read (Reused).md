
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 967.296 | 0.155351 | 191.274ms | 1691 | 1280 | 8586.3 | 1667.19 | 0.679512 | 3.10924 | 1(Win) | true |
| simdjson (ondemand) | 890.974 | 0.120231 | 210.912ms | 1691 | 2560 | 12123.5 | 1810 | 0.493923 | 3.37656 | 2(Loss) | true |
