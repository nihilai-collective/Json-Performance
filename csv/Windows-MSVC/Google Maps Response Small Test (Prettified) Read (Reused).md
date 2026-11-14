
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1355.41 | 0.193447 | 715.089ms | 9378 | 2560 | 417102 | 6598.4 | 0.335717 | 2.23495 | 1(Win) | true |
| simdjson (ondemand) | 1196.76 | 0.603666 | 802.26ms | 9378 | 160 | 325625 | 7473.12 | 0.0250962 | 2.53359 | 2(Loss) | true |
