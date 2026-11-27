
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10103.9 | 0.153291 | 1140.8ms | 108313 | 30 | 7367.82 | 10223.3 | 0 | 0.299609 | 1(Win) | true |
| simdjson (stage-1) DID NOT CONVERGE | 8005.42 | 1.42424 | 1256.75ms | 108313 | 4890 | 1.65145e+08 | 12903.2 | 2.92046 | 0.378353 | -(Loss) | false |
