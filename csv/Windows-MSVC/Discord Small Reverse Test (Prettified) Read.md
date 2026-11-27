
----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 650.787 | 0.067425 | 998.319ms | 6701 | 2560 | 112223 | 9819.77 | 0.0804191 | 4.66093 | 1(Win) | true |
| simdjson (ondemand) | 245.49 | 0.070727 | 2606.79ms | 6701 | 1280 | 433901 | 26031.9 | 0.197865 | 12.3714 | 2(Loss) | true |
