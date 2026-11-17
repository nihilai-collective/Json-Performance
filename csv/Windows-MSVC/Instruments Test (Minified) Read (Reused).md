
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1804.94 | 0.0917012 | 6129.28ms | 108313 | 2560 | 7.05056e+06 | 57229.1 | 0.0839575 | 1.37101 | 1(Win) | true |
| Jsonifier (two-stage) | 1302.89 | 0.193845 | 8334.41ms | 108313 | 1280 | 3.02318e+07 | 79281.4 | 0.28378 | 1.89953 | 2(Loss) | true |
| Glaze | 1052.51 | 0.196368 | 5394.3ms | 108313 | 320 | 1.18851e+07 | 98141.9 | 0.552882 | 2.3516 | 3(Loss) | true |
| simdjson (ondemand) | 779.979 | 0.194194 | 7138.4ms | 108313 | 320 | 2.11649e+07 | 132433 | 0.679888 | 3.17344 | 4(Loss) | true |
