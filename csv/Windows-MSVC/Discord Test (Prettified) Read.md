
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1263.53 | 0.181292 | 6453.48ms | 83958 | 1280 | 1.68936e+07 | 63369 | 0.269364 | 1.95856 | 1(Win) | true |
| simdjson (ondemand) | 1106.13 | 0.294732 | 7313.01ms | 83958 | 640 | 2.91302e+07 | 72385.9 | 0.535464 | 2.2373 | 2(Loss) | true |
