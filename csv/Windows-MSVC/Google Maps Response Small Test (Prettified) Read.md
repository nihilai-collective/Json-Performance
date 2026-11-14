
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2113.5 | 0.127526 | 427.219ms | 9378 | 2560 | 74551.4 | 4231.64 | 0.253572 | 1.43195 | 1(Win) | true |
| Jsonifier | 1955.41 | 0.208524 | 464.437ms | 9378 | 80 | 7276.9 | 4573.75 | 0.245365 | 1.55036 | 2(Loss) | true |
| Glaze | 1451.53 | 0.202996 | 620.14ms | 9378 | 2560 | 400485 | 6161.48 | 0.200739 | 2.08674 | 3(Loss) | true |
| simdjson (ondemand) | 1193.15 | 0.105256 | 754.728ms | 9378 | 2560 | 159353 | 7495.74 | 0.0850163 | 2.53956 | 4(Loss) | true |
