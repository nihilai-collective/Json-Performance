
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.706 | 0.211577 | 122.548ms | 905 | 320 | 1971.39 | 1173.12 | 0.0533049 | 4.06509 | 1(Win) | true |
| Glaze | 714.716 | 0.167482 | 127.093ms | 905 | 1280 | 5235.72 | 1207.58 | 0.457239 | 4.18244 | 2(Loss) | true |
| simdjson (ondemand) | 182.282 | 0.220193 | 471.822ms | 905 | 640 | 69566.5 | 4734.84 | 0.0560686 | 16.5953 | 3(Loss) | true |
