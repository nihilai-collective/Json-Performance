
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 296.1 | 0.0419602 | 1488.83ms | 4604 | 4890 | 189312 | 14828.5 | 0.102522 | 10.2505 | 1(Win) | true |
| simdjson (ondemand) | 281.125 | 0.6462 | 1577.12ms | 4604 | 4890 | 4.981e+07 | 15618.4 | 0.514021 | 10.7969 | 2(Loss) | true |
