
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.391 | 0.167575 | 1030.12ms | 9378 | 1280 | 359413 | 9999.61 | 0.799064 | 3.39083 | 1(Win) | true |
| simdjson (ondemand) | 879.764 | 0.122173 | 1005.22ms | 9378 | 2560 | 394895 | 10165.9 | 0.386508 | 3.44693 | 2(Loss) | true |
