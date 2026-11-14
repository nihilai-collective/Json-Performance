
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 908.749 | 0.654536 | 8201.83ms | 5212421 | 30 | 3.84574e+10 | 5.47011e+06 | 0.622415 | 3.34442 | 1(Win) | true |
| simdjson (ondemand) | 870.142 | 0.33067 | 8628.42ms | 5212421 | 80 | 2.85482e+10 | 5.71281e+06 | 1.01241 | 3.49284 | 2(Loss) | true |
