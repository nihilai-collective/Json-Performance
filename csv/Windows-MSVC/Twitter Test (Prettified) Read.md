
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22015.4 | 0.670698 | 2975.99ms | 631514 | 80 | 2.69312e+06 | 27356.2 | 0.936991 | 0.112312 | 1(Win) | true |
| simdjson (stage-1) | 18624.4 | 0.184082 | 3230.48ms | 631514 | 1280 | 4.53556e+06 | 32337 | 0.215484 | 0.132792 | 2(Loss) | true |
