
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9290.41 | 0.101717 | 6714.47ms | 631514 | 2560 | 1.11308e+07 | 64825.9 | 0.0521559 | 0.266373 | 1(Win) | true |
| Jsonifier | 9180.03 | 0.260985 | 6733.66ms | 631514 | 320 | 9.38119e+06 | 65605.3 | 0.153619 | 0.269552 | 2(Loss) | true |
| simdjson (ondemand) | 4315.99 | 0.416755 | 7091.41ms | 631514 | 80 | 2.70556e+07 | 139541 | 0.0707176 | 0.573504 | 3(Loss) | true |
| Glaze | 3431.07 | 0.157594 | 8973.61ms | 631514 | 1280 | 9.79483e+07 | 175531 | 0.298776 | 0.721474 | 4(Loss) | true |
