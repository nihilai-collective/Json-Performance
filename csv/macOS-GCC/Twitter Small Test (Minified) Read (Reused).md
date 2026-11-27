
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2961.27 | 1.11904 | 108.864ms | 2889 | 640 | 69376.2 | 930.4 | 0 | 1(Win) | true |
| Glaze | 2238.88 | 1.00242 | 135.583ms | 2889 | 1280 | 194781 | 1230.6 | 1.43422 | 2(Loss) | true |
| Jsonifier (two-stage) | 2180.06 | 0.7163 | 141.865ms | 2889 | 2560 | 209791 | 1263.8 | 0.253847 | 3(Loss) | true |
| simdjson (reflection) | 1555.57 | 0.391339 | 192.992ms | 2889 | 4890 | 234927 | 1771.16 | 0.725888 | 4(Loss) | true |
| simdjson (ondemand) | 1214.8 | 0.593273 | 241.125ms | 2889 | 1280 | 231743 | 2268 | 0.212089 | 5(Loss) | true |
