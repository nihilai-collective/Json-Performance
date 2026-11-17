
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1675.83 | 0.119459 | 167.873ms | 2889 | 640 | 2468.6 | 1644.06 | 0.227574 | 1.79303 | 1(Win) | true |
| Glaze | 1495.1 | 0.124168 | 187.074ms | 2889 | 4890 | 25602.7 | 1842.8 | 0.258686 | 2.01252 | 2(Loss) | true |
| Jsonifier (two-stage) | 1339.29 | 0.152316 | 208.926ms | 2889 | 1280 | 12567.5 | 2057.19 | 0.091227 | 2.24956 | 3(Loss) | true |
| simdjson (ondemand) | 1281.47 | 0.289694 | 216.857ms | 2889 | 320 | 12413.8 | 2150 | 0.0871333 | 2.34919 | 4(Loss) | true |
