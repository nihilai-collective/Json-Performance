
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 196.488 | 0.150031 | 461.208ms | 905 | 40 | 1737.18 | 4392.5 | 0.0189681 | 12.4915 | 1(Win) | true |
| simdjson (ondemand) | 66.7559 | 0.228363 | 1329.12ms | 905 | 1280 | 1.11578e+06 | 12928.8 | 0.0707496 | 36.952 | 2(Loss) | true |
