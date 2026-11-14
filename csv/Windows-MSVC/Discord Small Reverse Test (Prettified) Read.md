
----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.72 | 0.109087 | 1080.66ms | 6701 | 2560 | 355334 | 10800 | 0.0796351 | 5.12466 | 1(Win) | true |
| simdjson (ondemand) | 247.415 | 0.152269 | 2607.66ms | 6701 | 160 | 247496 | 25829.4 | 0.229347 | 12.2739 | 2(Loss) | true |
