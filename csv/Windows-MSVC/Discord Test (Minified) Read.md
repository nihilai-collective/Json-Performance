
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 899.615 | 0.122103 | 5993.57ms | 56369 | 2560 | 1.36289e+07 | 59756.3 | 0.0299957 | 3.37702 | 1(Win) | true |
| simdjson (ondemand) | 787.658 | 0.215586 | 6857.07ms | 56369 | 30 | 649483 | 68250 | 0.0292954 | 3.85741 | 2(Loss) | true |
