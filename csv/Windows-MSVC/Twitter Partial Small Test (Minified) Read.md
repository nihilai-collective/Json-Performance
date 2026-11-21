
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5366.93 | 0.185309 | 57.0403ms | 2889 | 1280 | 1158.37 | 513.359 | 0.348802 | 0.439636 | 1(Win) | true |
| Jsonifier | 5279.36 | 0.628209 | 56.097ms | 2889 | 160 | 1719.73 | 521.875 | 0.360577 | 0.442132 | 2(Loss) | true |
| simdjson (ondemand) | 3707.32 | 0.439645 | 86.4544ms | 2889 | 4890 | 52202.3 | 743.17 | 0.0480921 | 0.643884 | 3(Loss) | true |
| Glaze | 2775.11 | 0.324865 | 102.906ms | 2889 | 2560 | 26630.6 | 992.812 | 0.0708717 | 0.86826 | 4(Loss) | true |
