
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2207.9 | 1.08295 | 178.398ms | 3770 | 2560 | 796125 | 1628.4 | 0.258589 | 1(Win) | true |
| simdjson (ondemand) | 1785.89 | 0.489969 | 216.478ms | 3770 | 640 | 62271.9 | 2013.2 | 0.139276 | 2(Loss) | true |
