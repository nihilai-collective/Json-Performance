
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 20181.9 | 0.0395398 | 492.365ms | 108313 | 40 | 163.82 | 5118.23 | 0.0815048 | 0.121978 | 1(Win) | true |
| simdjson (stage-1) | 17120.3 | 0.0223087 | 610.791ms | 108313 | 80 | 144.937 | 6033.5 | 0.017814 | 0.144035 | 2(Loss) | true |
