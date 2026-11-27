
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 906.928 | 0.0956052 | 1305.66ms | 11812 | 4890 | 689561 | 12420.8 | 0.25515 | 1(Win) | true |
| simdjson (ondemand) | 815.025 | 0.137709 | 1399.27ms | 11812 | 640 | 231851 | 13821.4 | 0.0431129 | 2(Loss) | true |
