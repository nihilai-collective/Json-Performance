
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1552.69 | 0.120385 | 838.501ms | 11812 | 40 | 3051.28 | 7255 | 0.0689655 | 1.59093 | 1(Win) | true |
| Jsonifier (two-stage) | 1314.45 | 0.0504736 | 964.236ms | 11812 | 160 | 2993.71 | 8570 | 0.02918 | 1.87753 | 2(Loss) | true |
| Glaze | 991.448 | 0.123513 | 1243.81ms | 11812 | 4890 | 963036 | 11362 | 0.0047244 | 2.49103 | 3(Loss) | true |
| simdjson (ondemand) | 626.693 | 0.806317 | 1938.65ms | 11812 | 160 | 3.36101e+06 | 17975 | 0.195095 | 3.94622 | 4(Loss) | true |
