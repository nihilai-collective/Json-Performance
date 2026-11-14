
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.326 | 0.153051 | 443.892ms | 3770 | 4890 | 223838 | 4420.55 | 0.108928 | 3.72004 | 1(Win) | true |
| simdjson (ondemand) | 379.463 | 0.474592 | 957.911ms | 3770 | 640 | 1.29409e+06 | 9474.84 | 0.35003 | 7.99401 | 2(Loss) | true |
