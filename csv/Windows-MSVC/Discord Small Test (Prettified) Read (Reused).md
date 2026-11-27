
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2131.99 | 0.10513 | 365.017ms | 6701 | 2560 | 25421.5 | 2997.46 | 0.36229 | 1.416 | 1(Win) | true |
| Glaze | 1936.54 | 0.251653 | 394.379ms | 6701 | 30 | 2068.97 | 3300 | 0.801603 | 1.5626 | 2(Loss) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1644.97 | 1.18043 | 439.415ms | 6701 | 4890 | 1.02838e+07 | 3884.91 | 2.92212 | 1.83833 | -(Loss) | false |
| simdjson (ondemand) | 1453.5 | 0.17185 | 506.526ms | 6701 | 30 | 1712.64 | 4396.67 | 0.995406 | 2.0821 | 4(Loss) | true |
