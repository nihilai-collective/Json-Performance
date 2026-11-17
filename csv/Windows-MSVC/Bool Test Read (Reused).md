
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 250.076 | 0.0696793 | 358.553ms | 905 | 4890 | 28279.3 | 3451.25 | 0.447403 | 12.0866 | 1(Win) | true |
| simdjson (ondemand) | 123.289 | 1.24014 | 706.514ms | 905 | 4890 | 3.68554e+07 | 7000.43 | 0.242146 | 24.5789 | 2(Loss) | true |
