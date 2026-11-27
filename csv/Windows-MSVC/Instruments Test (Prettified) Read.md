
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 12733.3 | 0.3566 | 1506.5ms | 183677 | 30 | 72195.4 | 13756.7 | 0.578174 | 0.238015 | 1(Win) | true |
| simdjson (stage-1) | 10359 | 1.64604 | 1736.51ms | 183677 | 640 | 4.95827e+07 | 16909.7 | 0.0166297 | 0.292634 | 2(Loss) | true |
