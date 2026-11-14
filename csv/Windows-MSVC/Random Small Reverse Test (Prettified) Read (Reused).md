
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 910.347 | 0.121431 | 937.276ms | 8150 | 1280 | 137586 | 8537.89 | 0.0760059 | 3.33064 | 1(Win) | true |
| simdjson (ondemand) | 612.124 | 0.374398 | 1375.79ms | 8150 | 320 | 723191 | 12697.5 | 0.370535 | 4.95829 | 2(Loss) | true |
