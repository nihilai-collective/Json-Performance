
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 193.695 | 0.548133 | 7396.81ms | 2090234 | 30 | 9.54656e+10 | 1.02915e+07 | 1.91173 | 12.7821 | 1(Win) | true |
| simdjson (ondemand) | 183.176 | 0.606189 | 7599.13ms | 2090234 | 30 | 1.30554e+11 | 1.08825e+07 | 0.475025 | 13.5161 | 2(Loss) | true |
