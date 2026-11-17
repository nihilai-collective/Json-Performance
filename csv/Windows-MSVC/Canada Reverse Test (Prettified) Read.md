
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 456.753 | 0.521839 | 7605.22ms | 5212421 | 30 | 9.67632e+10 | 1.08832e+07 | 0.00300147 | 5.42042 | 1(Win) | true |
| simdjson (ondemand) | 436.218 | 0.782979 | 7954.89ms | 5212421 | 40 | 3.18443e+11 | 1.13956e+07 | 0.473009 | 5.67559 | 2(Loss) | true |
