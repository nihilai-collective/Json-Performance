
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 552.319 | 0.436932 | 9784.41ms | 108313 | 80 | 5.34194e+07 | 187021 | 0.00735265 | 5.50222 | 1(Win) | true |
| simdjson (ondemand) | 190.46 | 0.277569 | 7045.84ms | 108313 | 160 | 3.62591e+08 | 542347 | 0.114762 | 15.9576 | 2(Loss) | true |
