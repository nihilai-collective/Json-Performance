
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 737.785 | 0.141392 | 1633.67ms | 11812 | 2560 | 1.1931e+06 | 15268.4 | 0.0248102 | 4.11321 | 1(Win) | true |
| simdjson (ondemand) | 638.807 | 0.0485254 | 1857.49ms | 11812 | 4890 | 358059 | 17634.1 | 0.146688 | 4.75148 | 2(Loss) | true |
