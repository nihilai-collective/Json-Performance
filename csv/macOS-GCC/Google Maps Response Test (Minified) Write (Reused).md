
----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10308.2 | 0.556964 | 112.409ms | 11812 | 2560 | 94836.4 | 1092.8 | 0.459643 | 1(Win) | true |
| simdjson (reflection) | 9322.62 | 0.504712 | 124.067ms | 11812 | 4890 | 181873 | 1208.33 | 0.068776 | 2(Loss) | true |
| Glaze | 2011.98 | 0.160427 | 564.448ms | 11812 | 4890 | 394517 | 5598.86 | 0.163897 | 3(Loss) | true |
