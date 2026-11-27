
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3805.9 | 0.892995 | 74.6419ms | 2889 | 4890 | 204356 | 723.92 | 3.47625 | 1(Win) | true |
| Jsonifier | 3647.78 | 1.18818 | 77.4459ms | 2889 | 2560 | 206178 | 755.3 | 1.16528 | 2(Loss) | true |
| simdjson (reflection) | 3354.23 | 1.37344 | 81.8381ms | 2889 | 1280 | 162908 | 821.4 | 0.218659 | 3(Loss) | true |
| simdjson (ondemand) | 3121.1 | 0.65633 | 91.8341ms | 2889 | 4890 | 164147 | 882.755 | 0.814044 | 4(Loss) | true |
| Glaze | 2102.7 | 0.745067 | 132.165ms | 2889 | 2560 | 243990 | 1310.3 | 1.33283 | 5(Loss) | true |
